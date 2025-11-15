MiniDeps.later(function()
    vim.lsp.config('clangd', {
      cmd = {'devbox', 'run', 'clangd'}
    })

    local cppcheck_orig = require('lint').linters.cppcheck
    require('lint').linters.cppcheck = function()
      local linter = cppcheck_orig
      linter.cmd = 'script/run_cppcheck.sh'
      return linter
    end

    local cpplint_orig = require('lint').linters.cpplint
    require('lint').linters.cpplint = function()
      local linter = cpplint_orig
      linter.cmd = 'script/run_cpplint.sh'
      return linter
    end
end)
